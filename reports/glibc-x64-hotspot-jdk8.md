---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 07:41:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1794487017 12
1794487022 12
1794487027 12
1794487032 12
1794487037 12
1794487042 12
1794487047 32
1794487052 32
1794487057 32
1794487062 32
1794487067 32
1794487072 32
1794487077 32
1794487082 32
1794487087 32
1794487092 32
1794487097 32
1794487102 32
1794487107 32
1794487112 32
```
</details>

---

