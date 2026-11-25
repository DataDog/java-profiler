---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 13:28:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 63-79 cores)</summary>

```
1795630992 63
1795630997 63
1795631002 63
1795631007 63
1795631012 63
1795631017 63
1795631022 63
1795631027 63
1795631032 63
1795631037 63
1795631042 79
1795631047 79
1795631052 79
1795631057 79
1795631062 79
1795631067 79
1795631072 79
1795631077 79
1795631082 79
1795631087 79
```
</details>

---

