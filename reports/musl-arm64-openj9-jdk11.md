---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:48:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1017 |
| Sample Rate | 16.95/sec |
| Health Score | 1059% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795095795 50
1795095800 50
1795095805 50
1795095810 50
1795095815 45
1795095820 45
1795095825 45
1795095830 45
1795095835 45
1795095840 45
1795095845 45
1795095850 45
1795095855 45
1795095860 45
1795095865 45
1795095870 45
1795095875 45
1795095880 45
1795095885 45
1795095890 45
```
</details>

---

