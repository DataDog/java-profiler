---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 07:51:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 22-26 cores)</summary>

```
1777031172 24
1777031177 24
1777031182 24
1777031187 24
1777031192 24
1777031197 24
1777031202 24
1777031207 24
1777031212 24
1777031217 24
1777031222 24
1777031227 24
1777031232 24
1777031238 24
1777031243 24
1777031248 24
1777031253 24
1777031258 22
1777031263 22
1777031268 24
```
</details>

---

