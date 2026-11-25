---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 07:51:08 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795610801 60
1795610806 60
1795610811 60
1795610816 60
1795610821 60
1795610826 64
1795610831 64
1795610837 64
1795610842 64
1795610847 64
1795610852 64
1795610857 64
1795610862 64
1795610867 64
1795610872 64
1795610877 64
1795610882 64
1795610887 64
1795610892 64
1795610897 64
```
</details>

---

