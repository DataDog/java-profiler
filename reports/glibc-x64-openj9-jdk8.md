---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-28 18:13:25 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 82-92 cores)</summary>

```
1777414057 82
1777414062 82
1777414067 82
1777414072 87
1777414077 87
1777414082 83
1777414087 83
1777414092 88
1777414097 88
1777414102 88
1777414107 88
1777414112 88
1777414117 92
1777414122 92
1777414127 92
1777414132 92
1777414137 92
1777414142 92
1777414147 92
1777414152 92
```
</details>

---

