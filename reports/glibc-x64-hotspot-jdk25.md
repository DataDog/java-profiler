---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 00:58:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 42-94 cores)</summary>

```
1790312076 42
1790312081 42
1790312086 42
1790312091 42
1790312096 42
1790312101 42
1790312106 74
1790312111 74
1790312116 74
1790312121 74
1790312126 74
1790312131 80
1790312136 80
1790312141 88
1790312146 88
1790312151 88
1790312156 88
1790312161 88
1790312166 88
1790312171 94
```
</details>

---

