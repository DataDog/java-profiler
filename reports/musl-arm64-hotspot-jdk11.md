---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 11:10:42 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (5 unique values: 41-47 cores)</summary>

```
1787324724 44
1787324729 44
1787324734 44
1787324739 44
1787324744 44
1787324749 44
1787324754 44
1787324759 44
1787324764 44
1787324769 44
1787324774 44
1787324779 44
1787324784 44
1787324789 43
1787324794 43
1787324799 42
1787324804 42
1787324809 42
1787324814 41
1787324819 41
```
</details>

---

