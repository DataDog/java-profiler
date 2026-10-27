---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 11:01:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793112863 32
1793112868 32
1793112873 32
1793112878 32
1793112883 32
1793112888 32
1793112893 32
1793112898 32
1793112903 32
1793112908 32
1793112913 32
1793112918 32
1793112923 32
1793112928 32
1793112933 32
1793112938 32
1793112943 32
1793112948 32
1793112953 32
1793112958 32
```
</details>

---

