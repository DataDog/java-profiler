---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 11:32:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 65-84 cores)</summary>

```
1795192106 65
1795192111 67
1795192116 67
1795192121 67
1795192126 69
1795192131 69
1795192136 84
1795192141 84
1795192146 84
1795192151 84
1795192156 84
1795192161 84
1795192166 84
1795192171 65
1795192176 65
1795192181 65
1795192186 65
1795192191 65
1795192196 65
1795192201 68
```
</details>

---

