---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 14:36:17 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1792434743 47
1792434748 47
1792434753 47
1792434758 47
1792434763 47
1792434768 45
1792434773 45
1792434778 45
1792434783 45
1792434788 45
1792434793 45
1792434798 45
1792434803 45
1792434808 42
1792434813 42
1792434818 42
1792434823 42
1792434828 42
1792434833 42
1792434838 42
```
</details>

---

