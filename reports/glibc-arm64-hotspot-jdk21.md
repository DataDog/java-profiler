---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 08:47:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 25-43 cores)</summary>

```
1794922863 25
1794922868 25
1794922873 25
1794922878 25
1794922883 25
1794922888 30
1794922893 30
1794922898 30
1794922903 30
1794922908 30
1794922913 30
1794922918 30
1794922923 30
1794922928 30
1794922933 30
1794922938 30
1794922943 30
1794922948 30
1794922953 30
1794922958 43
```
</details>

---

