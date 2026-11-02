---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:55:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 11 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793634663 51
1793634668 51
1793634673 51
1793634678 51
1793634683 51
1793634688 51
1793634693 51
1793634699 51
1793634704 51
1793634709 51
1793634714 51
1793634719 51
1793634724 51
1793634729 51
1793634734 51
1793634739 51
1793634744 51
1793634749 51
1793634754 51
1793634759 51
```
</details>

---

