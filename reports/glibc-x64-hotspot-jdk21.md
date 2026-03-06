---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 04:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 953 |
| Sample Rate | 15.88/sec |
| Health Score | 993% |
| Threads | 12 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 80-84 cores)</summary>

```
1772790187 84
1772790192 84
1772790197 80
1772790202 80
1772790207 80
1772790212 80
1772790217 80
1772790222 80
1772790227 80
1772790232 80
1772790237 80
1772790242 80
1772790247 80
1772790252 80
1772790257 80
1772790262 80
1772790267 80
1772790272 80
1772790277 80
1772790282 80
```
</details>

---

