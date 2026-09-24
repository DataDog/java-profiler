---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 11:09:35 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 55-61 cores)</summary>

```
1790262201 57
1790262206 57
1790262211 55
1790262216 55
1790262221 55
1790262226 55
1790262231 55
1790262236 55
1790262241 55
1790262246 57
1790262251 57
1790262256 57
1790262261 57
1790262266 59
1790262271 59
1790262276 59
1790262281 60
1790262286 60
1790262291 60
1790262296 60
```
</details>

---

