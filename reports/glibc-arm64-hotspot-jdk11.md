---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:18:55 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1795626759 36
1795626764 36
1795626769 36
1795626774 36
1795626779 36
1795626784 36
1795626789 36
1795626794 36
1795626799 36
1795626804 36
1795626809 36
1795626814 48
1795626819 48
1795626824 48
1795626829 39
1795626834 39
1795626839 39
1795626844 39
1795626849 39
1795626854 39
```
</details>

---

