---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 13:10:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790096709 38
1790096714 38
1790096719 38
1790096724 43
1790096729 43
1790096734 43
1790096739 43
1790096745 43
1790096750 43
1790096755 43
1790096760 43
1790096765 43
1790096770 43
1790096775 43
1790096780 43
1790096785 43
1790096790 43
1790096795 43
1790096800 43
1790096805 43
```
</details>

---

