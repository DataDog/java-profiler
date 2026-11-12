---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 00:08:58 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794459938 64
1794459943 64
1794459948 64
1794459953 64
1794459958 64
1794459963 64
1794459968 64
1794459973 64
1794459978 64
1794459983 64
1794459988 64
1794459993 64
1794459998 64
1794460003 64
1794460008 64
1794460013 64
1794460018 64
1794460023 64
1794460028 64
1794460033 64
```
</details>

---

