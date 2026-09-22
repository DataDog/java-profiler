---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 09:50:44 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 8 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790084756 43
1790084761 43
1790084766 43
1790084771 48
1790084776 48
1790084782 48
1790084787 48
1790084792 48
1790084797 48
1790084802 48
1790084807 48
1790084812 48
1790084817 48
1790084822 48
1790084827 48
1790084832 48
1790084837 48
1790084842 48
1790084847 48
1790084852 48
```
</details>

---

