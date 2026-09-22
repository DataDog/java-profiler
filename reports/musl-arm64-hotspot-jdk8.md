---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 12:32:54 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 40 |
| Sample Rate | 0.67/sec |
| Health Score | 42% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-49 cores)</summary>

```
1790093815 49
1790093820 49
1790093825 49
1790093830 49
1790093835 49
1790093840 49
1790093845 49
1790093850 49
1790093855 49
1790093860 49
1790093865 36
1790093870 36
1790093875 36
1790093880 36
1790093885 36
1790093890 36
1790093895 36
1790093900 36
1790093905 36
1790093910 36
```
</details>

---

