---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:40:58 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 11 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 12 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 31-44 cores)</summary>

```
1770827487 44
1770827492 40
1770827497 40
1770827502 40
1770827507 40
1770827512 40
1770827517 40
1770827522 40
1770827527 40
1770827532 40
1770827537 40
1770827542 40
1770827547 40
1770827552 40
1770827557 40
1770827562 36
1770827567 36
1770827572 36
1770827577 36
1770827582 36
```
</details>

---

