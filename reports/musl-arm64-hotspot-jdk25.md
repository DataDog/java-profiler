---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:56:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1795171821 9
1795171826 9
1795171831 9
1795171836 9
1795171841 9
1795171846 9
1795171851 29
1795171856 29
1795171861 29
1795171866 29
1795171871 29
1795171876 29
1795171881 29
1795171886 29
1795171891 29
1795171896 29
1795171901 29
1795171906 29
1795171911 29
1795171916 29
```
</details>

---

