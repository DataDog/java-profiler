---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:09:11 EDT

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1786971648 43
1786971653 43
1786971658 42
1786971663 42
1786971668 47
1786971673 47
1786971678 47
1786971683 47
1786971688 47
1786971693 48
1786971698 48
1786971703 48
1786971708 48
1786971713 48
1786971718 48
1786971723 46
1786971728 46
1786971733 46
1786971738 46
1786971743 46
```
</details>

---

