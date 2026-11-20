---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:12:57 EST

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
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795172831 50
1795172836 50
1795172841 50
1795172846 50
1795172851 50
1795172856 50
1795172861 50
1795172866 50
1795172871 50
1795172876 50
1795172881 50
1795172886 50
1795172891 50
1795172896 50
1795172901 50
1795172906 50
1795172911 50
1795172916 50
1795172921 50
1795172926 50
```
</details>

---

