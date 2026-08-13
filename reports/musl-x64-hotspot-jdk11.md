---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 04:53:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 50-59 cores)</summary>

```
1786610838 57
1786610843 57
1786610848 57
1786610853 57
1786610858 57
1786610863 57
1786610868 57
1786610873 57
1786610878 57
1786610883 57
1786610888 57
1786610893 57
1786610898 57
1786610903 57
1786610908 59
1786610913 59
1786610918 59
1786610923 59
1786610928 59
1786610933 59
```
</details>

---

