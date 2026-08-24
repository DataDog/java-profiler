---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-24 13:07:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 12 |
| Allocations | 96 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1787591005 44
1787591010 44
1787591015 44
1787591020 44
1787591025 44
1787591030 44
1787591035 44
1787591040 44
1787591045 44
1787591050 44
1787591055 44
1787591060 44
1787591065 44
1787591070 44
1787591075 44
1787591080 44
1787591085 44
1787591090 44
1787591095 44
1787591100 64
```
</details>

---

