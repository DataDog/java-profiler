---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-16 07:30:00 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 13 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1789557833 33
1789557838 33
1789557843 33
1789557848 64
1789557853 64
1789557858 64
1789557863 64
1789557868 64
1789557873 64
1789557878 64
1789557883 64
1789557888 64
1789557893 64
1789557898 64
1789557903 64
1789557908 64
1789557913 64
1789557918 64
1789557923 64
1789557928 64
```
</details>

---

