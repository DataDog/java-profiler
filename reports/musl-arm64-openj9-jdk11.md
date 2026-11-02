---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1793656921 43
1793656926 43
1793656931 43
1793656936 43
1793656941 43
1793656946 43
1793656951 43
1793656956 42
1793656961 42
1793656966 42
1793656971 42
1793656976 42
1793656981 42
1793656986 42
1793656991 42
1793656996 42
1793657001 42
1793657006 43
1793657011 43
1793657016 43
```
</details>

---

