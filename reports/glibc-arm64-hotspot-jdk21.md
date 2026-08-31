---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-31 05:50:53 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 15 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1788169495 32
1788169500 32
1788169505 32
1788169510 32
1788169515 32
1788169520 32
1788169525 32
1788169531 32
1788169536 32
1788169541 32
1788169546 32
1788169551 32
1788169556 32
1788169561 32
1788169566 32
1788169571 32
1788169576 32
1788169581 32
1788169586 32
1788169591 52
```
</details>

---

