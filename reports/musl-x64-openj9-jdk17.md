---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 06:35:15 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 12 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1790332136 72
1790332141 72
1790332146 72
1790332151 72
1790332156 72
1790332161 72
1790332166 72
1790332171 70
1790332176 70
1790332181 70
1790332186 70
1790332191 70
1790332196 70
1790332201 70
1790332206 70
1790332211 70
1790332216 70
1790332221 72
1790332226 72
1790332231 72
```
</details>

---

