---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-24 11:39:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 39-55 cores)</summary>

```
1795537843 39
1795537848 39
1795537853 39
1795537858 39
1795537863 39
1795537868 39
1795537873 39
1795537878 39
1795537883 39
1795537888 39
1795537893 39
1795537898 39
1795537903 39
1795537908 39
1795537913 39
1795537918 39
1795537923 39
1795537928 55
1795537933 55
1795537938 55
```
</details>

---

