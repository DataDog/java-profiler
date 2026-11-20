---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:32:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 62-66 cores)</summary>

```
1795192092 64
1795192097 64
1795192102 64
1795192107 62
1795192112 62
1795192117 62
1795192122 62
1795192127 62
1795192133 62
1795192138 62
1795192143 66
1795192148 66
1795192153 66
1795192158 66
1795192163 66
1795192168 66
1795192173 66
1795192178 63
1795192183 63
1795192188 63
```
</details>

---

