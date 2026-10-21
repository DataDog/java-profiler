---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 07:16:22 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 52-69 cores)</summary>

```
1792581017 67
1792581022 67
1792581027 67
1792581032 69
1792581037 69
1792581042 69
1792581047 69
1792581052 69
1792581057 69
1792581062 69
1792581067 69
1792581072 69
1792581077 69
1792581082 67
1792581087 67
1792581092 52
1792581097 52
1792581102 52
1792581107 52
1792581112 52
```
</details>

---

