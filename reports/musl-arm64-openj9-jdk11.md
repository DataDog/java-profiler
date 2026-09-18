---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:47:05 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
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
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789731707 48
1789731712 48
1789731717 48
1789731722 48
1789731727 48
1789731732 48
1789731737 48
1789731742 48
1789731747 46
1789731752 46
1789731757 46
1789731762 46
1789731767 46
1789731772 46
1789731777 46
1789731782 46
1789731787 46
1789731792 46
1789731797 46
1789731802 46
```
</details>

---

