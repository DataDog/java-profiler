---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 11:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 9 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1786547863 72
1786547868 72
1786547873 62
1786547878 62
1786547883 64
1786547888 64
1786547893 64
1786547898 64
1786547903 64
1786547908 64
1786547913 64
1786547918 64
1786547923 64
1786547928 64
1786547933 64
1786547938 64
1786547943 64
1786547948 64
1786547953 64
1786547958 64
```
</details>

---

