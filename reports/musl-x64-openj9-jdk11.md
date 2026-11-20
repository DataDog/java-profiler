---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:21:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 39 |
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
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 22-39 cores)</summary>

```
1795195012 31
1795195017 31
1795195022 31
1795195027 31
1795195032 31
1795195037 31
1795195042 31
1795195047 31
1795195052 22
1795195057 22
1795195062 22
1795195067 22
1795195072 22
1795195077 22
1795195082 22
1795195087 22
1795195092 22
1795195097 22
1795195102 22
1795195107 22
```
</details>

---

