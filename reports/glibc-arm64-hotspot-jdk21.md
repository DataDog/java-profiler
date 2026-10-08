---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 01:03:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1791435527 42
1791435532 42
1791435537 42
1791435542 42
1791435547 42
1791435552 42
1791435557 42
1791435562 42
1791435567 42
1791435572 42
1791435577 42
1791435582 42
1791435587 42
1791435592 42
1791435597 42
1791435602 42
1791435607 42
1791435612 42
1791435617 37
1791435622 37
```
</details>

---

