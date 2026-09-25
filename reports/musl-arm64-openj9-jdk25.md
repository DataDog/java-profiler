---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 06:49:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 12 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 42-50 cores)</summary>

```
1790332981 50
1790332986 50
1790332991 50
1790332996 50
1790333001 50
1790333006 50
1790333011 50
1790333016 42
1790333021 42
1790333026 42
1790333031 42
1790333036 42
1790333041 42
1790333046 42
1790333051 42
1790333056 42
1790333061 42
1790333066 42
1790333071 42
1790333076 42
```
</details>

---

