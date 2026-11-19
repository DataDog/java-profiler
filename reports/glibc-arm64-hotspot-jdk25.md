---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:35:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 6 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795112810 47
1795112815 47
1795112820 47
1795112825 47
1795112830 47
1795112835 47
1795112840 42
1795112845 42
1795112850 42
1795112855 42
1795112860 42
1795112865 42
1795112870 42
1795112875 42
1795112880 42
1795112885 42
1795112890 42
1795112895 42
1795112900 47
1795112905 47
```
</details>

---

