---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 09:18:51 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 41-64 cores)</summary>

```
1792415648 41
1792415653 41
1792415658 41
1792415663 41
1792415668 41
1792415673 41
1792415678 41
1792415683 41
1792415688 41
1792415693 41
1792415698 52
1792415703 52
1792415708 52
1792415713 52
1792415718 52
1792415723 64
1792415728 64
1792415733 64
1792415738 64
1792415743 64
```
</details>

---

