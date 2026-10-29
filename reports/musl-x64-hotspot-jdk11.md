---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 12:44:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1793291792 63
1793291797 61
1793291802 61
1793291807 61
1793291812 61
1793291817 61
1793291822 61
1793291827 61
1793291832 61
1793291837 61
1793291842 61
1793291847 61
1793291852 61
1793291857 61
1793291862 61
1793291867 61
1793291872 61
1793291877 61
1793291882 61
1793291887 61
```
</details>

---

