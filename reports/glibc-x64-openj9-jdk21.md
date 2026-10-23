---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 19:01:52 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 53-96 cores)</summary>

```
1792796176 96
1792796181 96
1792796186 96
1792796191 96
1792796196 96
1792796201 96
1792796206 96
1792796211 57
1792796216 57
1792796221 57
1792796226 57
1792796231 57
1792796236 57
1792796241 57
1792796246 57
1792796251 57
1792796256 57
1792796261 55
1792796266 55
1792796271 55
```
</details>

---

