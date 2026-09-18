---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:32:47 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789712699 43
1789712704 43
1789712709 43
1789712714 43
1789712719 43
1789712724 48
1789712729 48
1789712734 48
1789712739 48
1789712744 48
1789712749 48
1789712754 48
1789712759 48
1789712764 48
1789712769 48
1789712774 48
1789712779 48
1789712784 48
1789712789 48
1789712794 48
```
</details>

---

