---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 11:01:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1793112878 48
1793112883 48
1793112888 48
1793112893 48
1793112898 48
1793112903 48
1793112908 48
1793112913 48
1793112918 48
1793112923 48
1793112928 48
1793112933 48
1793112938 48
1793112943 48
1793112948 48
1793112953 48
1793112958 40
1793112963 40
1793112968 40
1793112973 40
```
</details>

---

