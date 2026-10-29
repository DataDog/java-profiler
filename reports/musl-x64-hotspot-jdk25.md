---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 11:32:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1793287606 27
1793287611 27
1793287616 27
1793287621 27
1793287626 27
1793287631 27
1793287636 27
1793287641 27
1793287646 27
1793287651 27
1793287656 27
1793287661 27
1793287666 27
1793287671 27
1793287676 27
1793287681 25
1793287686 25
1793287691 25
1793287696 25
1793287701 25
```
</details>

---

