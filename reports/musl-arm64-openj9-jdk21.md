---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 16:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1786999820 34
1786999825 34
1786999830 34
1786999835 34
1786999840 34
1786999845 34
1786999850 34
1786999855 34
1786999860 34
1786999865 34
1786999870 34
1786999875 34
1786999880 34
1786999885 34
1786999890 34
1786999895 34
1786999900 34
1786999906 29
1786999911 29
1786999916 29
```
</details>

---

