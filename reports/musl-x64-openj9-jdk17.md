---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 12:00:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 59-87 cores)</summary>

```
1795452898 59
1795452903 59
1795452908 59
1795452913 59
1795452918 76
1795452923 76
1795452928 85
1795452933 85
1795452938 85
1795452944 85
1795452949 87
1795452954 87
1795452959 87
1795452964 87
1795452969 87
1795452974 87
1795452979 87
1795452984 87
1795452989 87
1795452994 87
```
</details>

---

