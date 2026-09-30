---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 13:02:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790787460 48
1790787465 48
1790787470 48
1790787475 48
1790787480 48
1790787485 48
1790787490 48
1790787495 48
1790787500 48
1790787505 48
1790787510 48
1790787515 48
1790787520 48
1790787525 48
1790787530 48
1790787535 48
1790787540 48
1790787545 43
1790787550 43
1790787555 43
```
</details>

---

