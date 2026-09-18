---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:29:45 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1789712719 29
1789712724 29
1789712729 29
1789712734 29
1789712739 29
1789712744 29
1789712749 29
1789712754 29
1789712759 29
1789712764 29
1789712769 34
1789712774 34
1789712779 34
1789712784 34
1789712789 34
1789712794 34
1789712799 34
1789712804 34
1789712809 34
1789712814 34
```
</details>

---

