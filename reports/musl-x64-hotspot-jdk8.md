---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-13 04:53:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 7 |
| Allocations | 0 |

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

