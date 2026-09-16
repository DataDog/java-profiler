---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-16 07:30:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1041 |
| Sample Rate | 17.35/sec |
| Health Score | 1084% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 19-42 cores)</summary>

```
1789557818 42
1789557823 42
1789557828 42
1789557833 42
1789557838 42
1789557843 42
1789557848 42
1789557853 42
1789557858 42
1789557863 42
1789557868 42
1789557873 42
1789557878 19
1789557883 19
1789557888 19
1789557893 19
1789557898 19
1789557903 19
1789557908 19
1789557913 19
```
</details>

---

