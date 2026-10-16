---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 09:13:23 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 12 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1792156132 92
1792156137 92
1792156142 92
1792156147 92
1792156152 92
1792156157 92
1792156162 90
1792156167 90
1792156172 90
1792156177 90
1792156182 90
1792156187 90
1792156192 90
1792156197 92
1792156202 92
1792156207 94
1792156212 94
1792156217 94
1792156222 96
1792156227 96
```
</details>

---

