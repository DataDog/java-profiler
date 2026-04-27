---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 14:05:04 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777312772 64
1777312777 64
1777312782 64
1777312787 64
1777312792 64
1777312797 64
1777312802 64
1777312807 64
1777312812 64
1777312817 64
1777312822 64
1777312827 64
1777312832 64
1777312837 64
1777312842 64
1777312847 64
1777312852 64
1777312857 64
1777312862 64
1777312867 64
```
</details>

---

