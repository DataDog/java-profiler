---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:29:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 11 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789712742 43
1789712747 43
1789712752 43
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
1789712807 48
1789712812 48
1789712817 48
1789712822 48
1789712827 48
1789712832 48
1789712837 48
```
</details>

---

