---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:23:36 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1795195139 57
1795195144 57
1795195149 55
1795195154 55
1795195159 55
1795195164 55
1795195169 55
1795195174 55
1795195179 55
1795195184 55
1795195189 55
1795195194 55
1795195199 55
1795195204 55
1795195209 55
1795195214 55
1795195219 55
1795195224 55
1795195229 55
1795195234 55
```
</details>

---

