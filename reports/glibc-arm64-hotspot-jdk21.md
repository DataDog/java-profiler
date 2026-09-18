---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:29:43 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789712757 43
1789712762 43
1789712767 43
1789712772 43
1789712777 43
1789712782 43
1789712787 43
1789712792 43
1789712797 43
1789712802 43
1789712807 43
1789712812 43
1789712817 43
1789712822 43
1789712827 43
1789712832 43
1789712837 43
1789712842 48
1789712847 48
1789712852 48
```
</details>

---

