---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 08:36:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 7 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 28-43 cores)</summary>

```
1791462749 43
1791462754 33
1791462759 33
1791462764 28
1791462769 28
1791462774 28
1791462779 28
1791462785 28
1791462790 28
1791462795 28
1791462800 28
1791462805 28
1791462810 28
1791462815 28
1791462820 28
1791462825 28
1791462830 28
1791462835 28
1791462840 28
1791462845 28
```
</details>

---

