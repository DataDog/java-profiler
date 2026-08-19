---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 01:04:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 11 |
| Allocations | 206 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1787115674 24
1787115679 24
1787115684 34
1787115689 34
1787115694 34
1787115699 34
1787115704 34
1787115709 34
1787115714 34
1787115719 34
1787115724 34
1787115730 34
1787115735 34
1787115740 34
1787115745 29
1787115750 29
1787115755 29
1787115760 29
1787115765 29
1787115770 29
```
</details>

---

