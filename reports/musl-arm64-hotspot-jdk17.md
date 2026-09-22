---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 09:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1790084758 49
1790084763 49
1790084768 49
1790084773 49
1790084778 49
1790084783 49
1790084788 49
1790084793 49
1790084798 49
1790084803 49
1790084808 49
1790084813 49
1790084818 49
1790084823 49
1790084828 64
1790084833 64
1790084838 64
1790084843 64
1790084848 64
1790084853 64
```
</details>

---

